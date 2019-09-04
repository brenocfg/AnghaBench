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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BUFDATALEN ; 
 int GENMASK (int,int) ; 
 int GET_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SIZE_16K ; 
 int SIZE_2K ; 
 int SIZE_4K ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u16 xgene_enet_get_data_len(u64 bufdatalen)
{
	u16 hw_len, mask;

	hw_len = GET_VAL(BUFDATALEN, bufdatalen);

	if (unlikely(hw_len == 0x7800)) {
		return 0;
	} else if (!(hw_len & BIT(14))) {
		mask = GENMASK(13, 0);
		return (hw_len & mask) ? (hw_len & mask) : SIZE_16K;
	} else if (!(hw_len & GENMASK(13, 12))) {
		mask = GENMASK(11, 0);
		return (hw_len & mask) ? (hw_len & mask) : SIZE_4K;
	} else {
		mask = GENMASK(11, 0);
		return (hw_len & mask) ? (hw_len & mask) : SIZE_2K;
	}
}