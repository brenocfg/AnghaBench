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
typedef  scalar_t__ u32 ;
struct sudmac_chan {scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ SUDMAC_CH0DEN ; 
 scalar_t__ sudmac_readl (struct sudmac_chan*,scalar_t__) ; 

__attribute__((used)) static bool sudmac_is_busy(struct sudmac_chan *sc)
{
	u32 den = sudmac_readl(sc, SUDMAC_CH0DEN + sc->offset);

	if (den)
		return true; /* working */

	return false; /* waiting */
}