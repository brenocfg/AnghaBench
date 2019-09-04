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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int mode; int /*<<< orphan*/  unit; int /*<<< orphan*/  port; int /*<<< orphan*/  device; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int TEST_LEN ; 
 int /*<<< orphan*/  WR (int,int) ; 
 int /*<<< orphan*/  bpck_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  bpck_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  bpck_force_spp (TYPE_1__*) ; 
 char j44 (int,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 char r0 () ; 
 int r1 () ; 
 char r4 () ; 
 int /*<<< orphan*/  r4l () ; 
 int /*<<< orphan*/  r4w () ; 
 int /*<<< orphan*/  t2 (int) ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static int bpck_test_proto( PIA *pi, char * scratch, int verbose )

{	int i, e, l, h, om;
	char buf[TEST_LEN];

	bpck_force_spp(pi);

	switch (pi->mode) {

	case 0: bpck_connect(pi);
		WR(0x13,0x7f);
		w0(0x13); t2(2);
		for(i=0;i<TEST_LEN;i++) {
                    t2(4); l = r1();
                    t2(4); h = r1();
                    buf[i] = j44(l,h);
		}
		bpck_disconnect(pi);
		break;

        case 1: bpck_connect(pi);
		WR(0x13,0x7f);
                w0(0x13); t2(2); t2(0x20);
                for(i=0;i<TEST_LEN;i++) { t2(4); buf[i] = r0(); }
                t2(1); t2(0x20);
		bpck_disconnect(pi);
		break;

	case 2:
	case 3:
	case 4: om = pi->mode;
		pi->mode = 0;
		bpck_connect(pi);
		WR(7,3);
		WR(4,8);
		bpck_disconnect(pi);

		pi->mode = om;
		bpck_connect(pi);
		w0(0x13); w2(9); w2(1); w0(0); w2(3); w2(0); w2(0xe0);

		switch (pi->mode) {
		  case 2: for (i=0;i<TEST_LEN;i++) buf[i] = r4();
			  break;
		  case 3: for (i=0;i<TEST_LEN/2;i++) ((u16 *)buf)[i] = r4w();
                          break;
		  case 4: for (i=0;i<TEST_LEN/4;i++) ((u32 *)buf)[i] = r4l();
                          break;
		}

		w2(0);
		WR(7,0);
		bpck_disconnect(pi);

		break;

	}

	if (verbose) {
	    printk("%s: bpck: 0x%x unit %d mode %d: ",
		   pi->device,pi->port,pi->unit,pi->mode);
	    for (i=0;i<TEST_LEN;i++) printk("%3d",buf[i]);
	    printk("\n");
	}

	e = 0;
	for (i=0;i<TEST_LEN;i++) if (buf[i] != (i+1)) e++;
	return e;
}