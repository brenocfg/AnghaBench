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
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL (struct parport*) ; 
 int PARPORT_MODE_PCSPP ; 
 int /*<<< orphan*/  clear_epp_timeout (struct parport*) ; 
 unsigned char parport_gsc_read_data (struct parport*) ; 
 int /*<<< orphan*/  parport_gsc_write_data (struct parport*,unsigned char) ; 
 unsigned char parport_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parport_SPP_supported(struct parport *pb)
{
	unsigned char r, w;

	/*
	 * first clear an eventually pending EPP timeout 
	 * I (sailer@ife.ee.ethz.ch) have an SMSC chipset
	 * that does not even respond to SPP cycles if an EPP
	 * timeout is pending
	 */
	clear_epp_timeout(pb);

	/* Do a simple read-write test to make sure the port exists. */
	w = 0xc;
	parport_writeb (w, CONTROL (pb));

	/* Is there a control register that we can read from?  Some
	 * ports don't allow reads, so read_control just returns a
	 * software copy. Some ports _do_ allow reads, so bypass the
	 * software copy here.  In addition, some bits aren't
	 * writable. */
	r = parport_readb (CONTROL (pb));
	if ((r & 0xf) == w) {
		w = 0xe;
		parport_writeb (w, CONTROL (pb));
		r = parport_readb (CONTROL (pb));
		parport_writeb (0xc, CONTROL (pb));
		if ((r & 0xf) == w)
			return PARPORT_MODE_PCSPP;
	}

	/* Try the data register.  The data lines aren't tri-stated at
	 * this stage, so we expect back what we wrote. */
	w = 0xaa;
	parport_gsc_write_data (pb, w);
	r = parport_gsc_read_data (pb);
	if (r == w) {
		w = 0x55;
		parport_gsc_write_data (pb, w);
		r = parport_gsc_read_data (pb);
		if (r == w)
			return PARPORT_MODE_PCSPP;
	}

	return 0;
}