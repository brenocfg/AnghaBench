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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sunxi_nfc_randomizer_state (struct nand_chip*,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_step (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sunxi_nfc_randomize_bbm(struct nand_chip *nand, int page, u8 *bbm)
{
	u16 state = sunxi_nfc_randomizer_state(nand, page, true);

	bbm[0] ^= state;
	bbm[1] ^= sunxi_nfc_randomizer_step(state, 8);
}