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
typedef  int u32 ;
struct send_context {int credits; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIO_BLOCK_SIZE ; 

u32 sc_mtu_to_threshold(struct send_context *sc, u32 mtu, u32 hdrqentsize)
{
	u32 release_credits;
	u32 threshold;

	/* add in the header size, then divide by the PIO block size */
	mtu += hdrqentsize << 2;
	release_credits = DIV_ROUND_UP(mtu, PIO_BLOCK_SIZE);

	/* check against this context's credits */
	if (sc->credits <= release_credits)
		threshold = 1;
	else
		threshold = sc->credits - release_credits;

	return threshold;
}