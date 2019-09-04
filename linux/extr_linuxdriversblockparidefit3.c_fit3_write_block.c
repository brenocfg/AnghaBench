#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  w0 (char) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w4 (char) ; 

__attribute__((used)) static void fit3_write_block( PIA *pi, char * buf, int count )

{	int k;

        switch (pi->mode) {

	case 0:
        case 1: w2(0xc); w0(0); w2(0x8); w2(0xc);
                for (k=0;k<count/2;k++) {
 		    w0(buf[2*k  ]); w2(0xd);
 		    w0(buf[2*k+1]); w2(0xc);
		}
		break;

        case 2: w2(0xc); w0(0); w2(0x8); w2(0xc); 
                for (k=0;k<count;k++) w4(buf[k]);
                w2(0xc);
		break;
	}
}