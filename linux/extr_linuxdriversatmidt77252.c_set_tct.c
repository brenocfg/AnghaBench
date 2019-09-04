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
struct vc_map {int index; int class; int init_er; TYPE_1__* scq; } ;
struct idt77252_dev {int /*<<< orphan*/  name; scalar_t__ tct_base; } ;
struct TYPE_2__ {int scd; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  OPRINTK (char*,int /*<<< orphan*/ ,unsigned long,int) ; 
 int SAR_SRAM_TCT_SIZE ; 
#define  SCHED_ABR 131 
#define  SCHED_CBR 130 
#define  SCHED_UBR 129 
#define  SCHED_VBR 128 
 int TCT_CBR ; 
 int TCT_FLAG_UBR ; 
 int TCT_HALT ; 
 int TCT_IDLE ; 
 int TCT_TSIF ; 
 int TCT_UBR ; 
 int /*<<< orphan*/  write_sram (struct idt77252_dev*,unsigned long,int) ; 

__attribute__((used)) static int
set_tct(struct idt77252_dev *card, struct vc_map *vc)
{
	unsigned long tct;

	tct = (unsigned long) (card->tct_base + vc->index * SAR_SRAM_TCT_SIZE);

	switch (vc->class) {
	case SCHED_CBR:
		OPRINTK("%s: writing TCT at 0x%lx, SCD 0x%lx.\n",
		        card->name, tct, vc->scq->scd);

		write_sram(card, tct + 0, TCT_CBR | vc->scq->scd);
		write_sram(card, tct + 1, 0);
		write_sram(card, tct + 2, 0);
		write_sram(card, tct + 3, 0);
		write_sram(card, tct + 4, 0);
		write_sram(card, tct + 5, 0);
		write_sram(card, tct + 6, 0);
		write_sram(card, tct + 7, 0);
		break;

	case SCHED_UBR:
		OPRINTK("%s: writing TCT at 0x%lx, SCD 0x%lx.\n",
		        card->name, tct, vc->scq->scd);

		write_sram(card, tct + 0, TCT_UBR | vc->scq->scd);
		write_sram(card, tct + 1, 0);
		write_sram(card, tct + 2, TCT_TSIF);
		write_sram(card, tct + 3, TCT_HALT | TCT_IDLE);
		write_sram(card, tct + 4, 0);
		write_sram(card, tct + 5, vc->init_er);
		write_sram(card, tct + 6, 0);
		write_sram(card, tct + 7, TCT_FLAG_UBR);
		break;

	case SCHED_VBR:
	case SCHED_ABR:
	default:
		return -ENOSYS;
	}

	return 0;
}