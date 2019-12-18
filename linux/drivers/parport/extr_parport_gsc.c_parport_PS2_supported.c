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
struct parport_gsc_private {int ctr_writable; } ;
struct parport {struct parport_gsc_private* private_data; int /*<<< orphan*/  modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARPORT_MODE_TRISTATE ; 
 int /*<<< orphan*/  clear_epp_timeout (struct parport*) ; 
 int /*<<< orphan*/  parport_gsc_data_forward (struct parport*) ; 
 int /*<<< orphan*/  parport_gsc_data_reverse (struct parport*) ; 
 int parport_gsc_read_data (struct parport*) ; 
 int /*<<< orphan*/  parport_gsc_write_data (struct parport*,int) ; 

__attribute__((used)) static int parport_PS2_supported(struct parport *pb)
{
	int ok = 0;
  
	clear_epp_timeout(pb);

	/* try to tri-state the buffer */
	parport_gsc_data_reverse (pb);
	
	parport_gsc_write_data(pb, 0x55);
	if (parport_gsc_read_data(pb) != 0x55) ok++;

	parport_gsc_write_data(pb, 0xaa);
	if (parport_gsc_read_data(pb) != 0xaa) ok++;

	/* cancel input mode */
	parport_gsc_data_forward (pb);

	if (ok) {
		pb->modes |= PARPORT_MODE_TRISTATE;
	} else {
		struct parport_gsc_private *priv = pb->private_data;
		priv->ctr_writable &= ~0x20;
	}

	return ok;
}