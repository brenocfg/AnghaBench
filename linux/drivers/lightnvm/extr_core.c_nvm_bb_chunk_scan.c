#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pg; int pl; } ;
struct ppa_addr {TYPE_1__ g; } ;
struct nvm_geo {int num_pg; int num_pln; scalar_t__ ws_min; int /*<<< orphan*/  clba; } ;
struct nvm_dev {struct nvm_geo geo; } ;
struct nvm_chk_meta {int /*<<< orphan*/  wp; void* state; } ;

/* Variables and functions */
 void* NVM_CHK_ST_CLOSED ; 
 void* NVM_CHK_ST_FREE ; 
 void* NVM_CHK_ST_OPEN ; 
#define  NVM_RSP_ERR_EMPTYPAGE 131 
#define  NVM_RSP_ERR_FAILCRC 130 
#define  NVM_RSP_ERR_FAILECC 129 
#define  NVM_RSP_WARN_HIGHECC 128 
 int nvm_bb_chunk_sense (struct nvm_dev*,struct ppa_addr) ; 

__attribute__((used)) static int nvm_bb_chunk_scan(struct nvm_dev *dev, struct ppa_addr ppa,
			     struct nvm_chk_meta *meta)
{
	struct nvm_geo *geo = &dev->geo;
	int ret, pg, pl;

	/* sense first page */
	ret = nvm_bb_chunk_sense(dev, ppa);
	if (ret < 0) /* io error */
		return ret;
	else if (ret == 0) /* valid data */
		meta->state = NVM_CHK_ST_OPEN;
	else if (ret > 0) {
		/*
		 * If empty page, the chunk is free, else it is an
		 * actual io error. In that case, mark it offline.
		 */
		switch (ret) {
		case NVM_RSP_ERR_EMPTYPAGE:
			meta->state = NVM_CHK_ST_FREE;
			return 0;
		case NVM_RSP_ERR_FAILCRC:
		case NVM_RSP_ERR_FAILECC:
		case NVM_RSP_WARN_HIGHECC:
			meta->state = NVM_CHK_ST_OPEN;
			goto scan;
		default:
			return -ret; /* other io error */
		}
	}

	/* sense last page */
	ppa.g.pg = geo->num_pg - 1;
	ppa.g.pl = geo->num_pln - 1;

	ret = nvm_bb_chunk_sense(dev, ppa);
	if (ret < 0) /* io error */
		return ret;
	else if (ret == 0) { /* Chunk fully written */
		meta->state = NVM_CHK_ST_CLOSED;
		meta->wp = geo->clba;
		return 0;
	} else if (ret > 0) {
		switch (ret) {
		case NVM_RSP_ERR_EMPTYPAGE:
		case NVM_RSP_ERR_FAILCRC:
		case NVM_RSP_ERR_FAILECC:
		case NVM_RSP_WARN_HIGHECC:
			meta->state = NVM_CHK_ST_OPEN;
			break;
		default:
			return -ret; /* other io error */
		}
	}

scan:
	/*
	 * chunk is open, we scan sequentially to update the write pointer.
	 * We make the assumption that targets write data across all planes
	 * before moving to the next page.
	 */
	for (pg = 0; pg < geo->num_pg; pg++) {
		for (pl = 0; pl < geo->num_pln; pl++) {
			ppa.g.pg = pg;
			ppa.g.pl = pl;

			ret = nvm_bb_chunk_sense(dev, ppa);
			if (ret < 0) /* io error */
				return ret;
			else if (ret == 0) {
				meta->wp += geo->ws_min;
			} else if (ret > 0) {
				switch (ret) {
				case NVM_RSP_ERR_EMPTYPAGE:
					return 0;
				case NVM_RSP_ERR_FAILCRC:
				case NVM_RSP_ERR_FAILECC:
				case NVM_RSP_WARN_HIGHECC:
					meta->wp += geo->ws_min;
					break;
				default:
					return -ret; /* other io error */
				}
			}
		}
	}

	return 0;
}