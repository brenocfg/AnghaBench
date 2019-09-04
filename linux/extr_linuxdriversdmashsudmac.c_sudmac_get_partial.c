#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_2__ {size_t base_byte_count; } ;
struct sudmac_desc {TYPE_1__ hw; } ;
struct sudmac_chan {scalar_t__ offset; } ;
struct shdma_desc {int dummy; } ;
struct shdma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ SUDMAC_CH0CBC ; 
 size_t sudmac_readl (struct sudmac_chan*,scalar_t__) ; 
 struct sudmac_chan* to_chan (struct shdma_chan*) ; 
 struct sudmac_desc* to_desc (struct shdma_desc*) ; 

__attribute__((used)) static size_t sudmac_get_partial(struct shdma_chan *schan,
				 struct shdma_desc *sdesc)
{
	struct sudmac_chan *sc = to_chan(schan);
	struct sudmac_desc *sd = to_desc(sdesc);
	u32 current_byte_count = sudmac_readl(sc, SUDMAC_CH0CBC + sc->offset);

	return sd->hw.base_byte_count - current_byte_count;
}