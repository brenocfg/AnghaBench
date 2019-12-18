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
struct reset_controller_dev {int dummy; } ;
struct brcmstb_reset {scalar_t__ base; } ;

/* Variables and functions */
 unsigned int SW_INIT_BANK (unsigned long) ; 
 unsigned int SW_INIT_BANK_SIZE ; 
 int /*<<< orphan*/  SW_INIT_BIT (unsigned long) ; 
 scalar_t__ SW_INIT_CLEAR ; 
 struct brcmstb_reset* to_brcmstb (struct reset_controller_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int brcmstb_reset_deassert(struct reset_controller_dev *rcdev,
				  unsigned long id)
{
	unsigned int off = SW_INIT_BANK(id) * SW_INIT_BANK_SIZE;
	struct brcmstb_reset *priv = to_brcmstb(rcdev);

	writel_relaxed(SW_INIT_BIT(id), priv->base + off + SW_INIT_CLEAR);
	/* Maximum reset delay after de-asserting a line and seeing block
	 * operation is typically 14us for the worst case, build some slack
	 * here.
	 */
	usleep_range(100, 200);

	return 0;
}