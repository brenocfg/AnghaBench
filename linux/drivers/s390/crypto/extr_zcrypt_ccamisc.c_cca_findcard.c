#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct secaeskeytoken {int /*<<< orphan*/  mkvp; } ;
struct keytoken_header {scalar_t__ type; int version; } ;
struct cipherkeytoken {int /*<<< orphan*/  mkvp0; } ;

/* Variables and functions */
 int AP_DEVICE_TYPE_CEX6 ; 
 int EINVAL ; 
 scalar_t__ TOKTYPE_CCA_INTERNAL ; 
#define  TOKVER_CCA_AES 129 
#define  TOKVER_CCA_VLSC 128 
 int findcard (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

int cca_findcard(const u8 *key, u16 *pcardnr, u16 *pdomain, int verify)
{
	u64 mkvp;
	int minhwtype = 0;
	const struct keytoken_header *hdr = (struct keytoken_header *) key;

	if (hdr->type != TOKTYPE_CCA_INTERNAL)
		return -EINVAL;

	switch (hdr->version) {
	case TOKVER_CCA_AES:
		mkvp = ((struct secaeskeytoken *)key)->mkvp;
		break;
	case TOKVER_CCA_VLSC:
		mkvp = ((struct cipherkeytoken *)key)->mkvp0;
		minhwtype = AP_DEVICE_TYPE_CEX6;
		break;
	default:
		return -EINVAL;
	}

	return findcard(mkvp, pcardnr, pdomain, verify, minhwtype);
}