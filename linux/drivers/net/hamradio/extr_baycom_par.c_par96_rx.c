#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct parport {TYPE_4__* ops; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int descram; int dcd_shreg; int dcd_count; } ;
struct TYPE_7__ {TYPE_2__ par96; } ;
struct baycom_state {int options; int /*<<< orphan*/  hdrv; TYPE_3__ modem; TYPE_1__* pdev; } ;
struct TYPE_8__ {int (* read_status ) (struct parport*) ;int /*<<< orphan*/  (* write_data ) (struct parport*,int) ;} ;
struct TYPE_5__ {struct parport* port; } ;

/* Variables and functions */
 int BAYCOM_OPTIONS_SOFTDCD ; 
 int HDLCDRV_MAXFLEN ; 
 int PAR96_BURST ; 
 int PAR96_BURSTBITS ; 
 int PAR96_DCD ; 
 unsigned int PAR96_DESCRAM_TAPSH1 ; 
 unsigned int PAR96_DESCRAM_TAPSH2 ; 
 int PAR96_PTT ; 
 int PAR96_RXBIT ; 
 int PAR97_POWER ; 
 int /*<<< orphan*/  hdlcdrv_putbits (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  hdlcdrv_setdcd (int /*<<< orphan*/ *,int) ; 
 int stub1 (struct parport*) ; 
 int /*<<< orphan*/  stub2 (struct parport*,int) ; 
 int /*<<< orphan*/  stub3 (struct parport*,int) ; 
 int stub4 (struct parport*) ; 

__attribute__((used)) static inline void par96_rx(struct net_device *dev, struct baycom_state *bc)
{
	int i;
	unsigned int data, mask, mask2, descx;
	struct parport *pp = bc->pdev->port;

	/*
	 * do receiver; differential decode and descramble on the fly
	 */
	for(data = i = 0; i < PAR96_BURSTBITS; i++) {
		bc->modem.par96.descram = (bc->modem.par96.descram << 1);
		if (pp->ops->read_status(pp) & PAR96_RXBIT)
			bc->modem.par96.descram |= 1;
		descx = bc->modem.par96.descram ^
			(bc->modem.par96.descram >> 1);
		/* now the diff decoded data is inverted in descram */
		pp->ops->write_data(pp, PAR97_POWER | PAR96_PTT);
		descx ^= ((descx >> PAR96_DESCRAM_TAPSH1) ^
			  (descx >> PAR96_DESCRAM_TAPSH2));
		data >>= 1;
		if (!(descx & 1))
			data |= 0x8000;
		pp->ops->write_data(pp, PAR97_POWER | PAR96_PTT | PAR96_BURST);
	}
	hdlcdrv_putbits(&bc->hdrv, data);
	/*
	 * do DCD algorithm
	 */
	if (bc->options & BAYCOM_OPTIONS_SOFTDCD) {
		bc->modem.par96.dcd_shreg = (bc->modem.par96.dcd_shreg >> 16)
			| (data << 16);
		/* search for flags and set the dcd counter appropriately */
		for(mask = 0x1fe00, mask2 = 0xfc00, i = 0;
		    i < PAR96_BURSTBITS; i++, mask <<= 1, mask2 <<= 1)
			if ((bc->modem.par96.dcd_shreg & mask) == mask2)
				bc->modem.par96.dcd_count = HDLCDRV_MAXFLEN+4;
		/* check for abort/noise sequences */
		for(mask = 0x1fe00, mask2 = 0x1fe00, i = 0;
		    i < PAR96_BURSTBITS; i++, mask <<= 1, mask2 <<= 1)
			if (((bc->modem.par96.dcd_shreg & mask) == mask2) &&
			    (bc->modem.par96.dcd_count >= 0))
				bc->modem.par96.dcd_count -= HDLCDRV_MAXFLEN-10;
		/* decrement and set the dcd variable */
		if (bc->modem.par96.dcd_count >= 0)
			bc->modem.par96.dcd_count -= 2;
		hdlcdrv_setdcd(&bc->hdrv, bc->modem.par96.dcd_count > 0);
	} else {
		hdlcdrv_setdcd(&bc->hdrv, !!(pp->ops->read_status(pp) & PAR96_DCD));
	}
}