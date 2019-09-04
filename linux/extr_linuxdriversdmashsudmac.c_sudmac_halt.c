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
struct sudmac_chan {int dummy; } ;
struct shdma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sudmac_dma_halt (struct sudmac_chan*) ; 
 struct sudmac_chan* to_chan (struct shdma_chan*) ; 

__attribute__((used)) static void sudmac_halt(struct shdma_chan *schan)
{
	struct sudmac_chan *sc = to_chan(schan);

	sudmac_dma_halt(sc);
}