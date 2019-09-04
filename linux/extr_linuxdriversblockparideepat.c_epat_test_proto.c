#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  port; int /*<<< orphan*/  device; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int RR (int) ; 
 int RRi (int) ; 
 int /*<<< orphan*/  WR (int,int) ; 
 int /*<<< orphan*/  WRi (int,int) ; 
 int /*<<< orphan*/  epat_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  epat_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  epat_read_block (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int epat_test_proto( PIA *pi, char * scratch, int verbose )

{       int     k, j, f, cc;
	int	e[2] = {0,0};

        epat_connect(pi);
	cc = RR(0xd);
	epat_disconnect(pi);

	epat_connect(pi);
	for (j=0;j<2;j++) {
  	    WRi(6,0xa0+j*0x10);
            for (k=0;k<256;k++) {
                WRi(2,k^0xaa);
                WRi(3,k^0x55);
                if (RRi(2) != (k^0xaa)) e[j]++;
                }
	    }
        epat_disconnect(pi);

        f = 0;
        epat_connect(pi);
        WR(0x13,1); WR(0x13,0); WR(0xa,0x11);
        epat_read_block(pi,scratch,512);
	
        for (k=0;k<256;k++) {
            if ((scratch[2*k] & 0xff) != k) f++;
            if ((scratch[2*k+1] & 0xff) != (0xff-k)) f++;
        }
        epat_disconnect(pi);

        if (verbose)  {
            printk("%s: epat: port 0x%x, mode %d, ccr %x, test=(%d,%d,%d)\n",
		   pi->device,pi->port,pi->mode,cc,e[0],e[1],f);
	}
	
        return (e[0] && e[1]) || f;
}