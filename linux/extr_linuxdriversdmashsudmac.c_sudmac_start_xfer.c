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
struct sudmac_desc {int /*<<< orphan*/  hw; } ;
struct sudmac_chan {int dummy; } ;
struct shdma_desc {int dummy; } ;
struct shdma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sudmac_set_reg (struct sudmac_chan*,int /*<<< orphan*/ *,struct shdma_desc*) ; 
 int /*<<< orphan*/  sudmac_start (struct sudmac_chan*) ; 
 struct sudmac_chan* to_chan (struct shdma_chan*) ; 
 struct sudmac_desc* to_desc (struct shdma_desc*) ; 

__attribute__((used)) static void sudmac_start_xfer(struct shdma_chan *schan,
			      struct shdma_desc *sdesc)
{
	struct sudmac_chan *sc = to_chan(schan);
	struct sudmac_desc *sd = to_desc(sdesc);

	sudmac_set_reg(sc, &sd->hw, sdesc);
	sudmac_start(sc);
}