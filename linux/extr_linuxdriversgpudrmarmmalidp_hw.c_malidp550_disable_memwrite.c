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
struct malidp_hw_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MALIDP550_SE_CONTROL ; 
 int MALIDP550_SE_MEMWRITE_ONESHOT ; 
 int /*<<< orphan*/  MALIDP_DE_BLOCK ; 
 scalar_t__ MALIDP_DE_DISPLAY_FUNC ; 
 int MALIDP_SCALE_ENGINE_EN ; 
 int MALIDP_SE_MEMWRITE_EN ; 
 scalar_t__ malidp_get_block_base (struct malidp_hw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_clearbits (struct malidp_hw_device*,int,scalar_t__) ; 

__attribute__((used)) static void malidp550_disable_memwrite(struct malidp_hw_device *hwdev)
{
	u32 base = malidp_get_block_base(hwdev, MALIDP_DE_BLOCK);

	malidp_hw_clearbits(hwdev, MALIDP550_SE_MEMWRITE_ONESHOT | MALIDP_SE_MEMWRITE_EN,
			    MALIDP550_SE_CONTROL);
	malidp_hw_clearbits(hwdev, MALIDP_SCALE_ENGINE_EN, base + MALIDP_DE_DISPLAY_FUNC);
}