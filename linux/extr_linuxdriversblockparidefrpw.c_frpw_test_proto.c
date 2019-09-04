#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int private; int port; int mode; int /*<<< orphan*/  device; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  frpw_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  frpw_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  frpw_read_block_int (TYPE_1__*,char*,int,int) ; 
 int frpw_read_regr (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int frpw_test_pnp (TYPE_1__*) ; 
 int /*<<< orphan*/  frpw_write_regr (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int frpw_test_proto( PIA *pi, char * scratch, int verbose )

{       int     j, k, r;
	int	e[2] = {0,0};

	if ((pi->private>>1) != pi->port)
	   pi->private = frpw_test_pnp(pi) + 2*pi->port;

	if (((pi->private%2) == 0) && (pi->mode > 2)) {
	   if (verbose) 
		printk("%s: frpw: Xilinx does not support mode %d\n",
			pi->device, pi->mode);
	   return 1;
	}

	if (((pi->private%2) == 1) && (pi->mode == 2)) {
	   if (verbose)
		printk("%s: frpw: ASIC does not support mode 2\n",
			pi->device);
	   return 1;
	}

	frpw_connect(pi);
	for (j=0;j<2;j++) {
                frpw_write_regr(pi,0,6,0xa0+j*0x10);
                for (k=0;k<256;k++) {
                        frpw_write_regr(pi,0,2,k^0xaa);
                        frpw_write_regr(pi,0,3,k^0x55);
                        if (frpw_read_regr(pi,0,2) != (k^0xaa)) e[j]++;
                        }
                }
	frpw_disconnect(pi);

	frpw_connect(pi);
        frpw_read_block_int(pi,scratch,512,0x10);
        r = 0;
        for (k=0;k<128;k++) if (scratch[k] != k) r++;
	frpw_disconnect(pi);

        if (verbose)  {
            printk("%s: frpw: port 0x%x, chip %ld, mode %d, test=(%d,%d,%d)\n",
                   pi->device,pi->port,(pi->private%2),pi->mode,e[0],e[1],r);
        }

        return (r || (e[0] && e[1]));
}