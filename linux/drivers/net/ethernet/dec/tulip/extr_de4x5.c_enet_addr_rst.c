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
typedef  int /*<<< orphan*/  u_long ;
typedef  void* u32 ;
typedef  char s8 ;

/* Variables and functions */
 void* ETH_PROM_SIG ; 
 short PROBE_LENGTH ; 
 char inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enet_addr_rst(u_long aprom_addr)
{
    union {
	struct {
	    u32 a;
	    u32 b;
	} llsig;
	char Sig[sizeof(u32) << 1];
    } dev;
    short sigLength=0;
    s8 data;
    int i, j;

    dev.llsig.a = ETH_PROM_SIG;
    dev.llsig.b = ETH_PROM_SIG;
    sigLength = sizeof(u32) << 1;

    for (i=0,j=0;j<sigLength && i<PROBE_LENGTH+sigLength-1;i++) {
	data = inb(aprom_addr);
	if (dev.Sig[j] == data) {    /* track signature */
	    j++;
	} else {                     /* lost signature; begin search again */
	    if (data == dev.Sig[0]) {  /* rare case.... */
		j=1;
	    } else {
		j=0;
	    }
	}
    }
}