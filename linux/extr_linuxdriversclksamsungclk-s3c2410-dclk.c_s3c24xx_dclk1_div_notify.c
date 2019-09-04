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
struct s3c24xx_dclk {int dummy; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCLKCON_DCLK1_CMP_SHIFT ; 
 int /*<<< orphan*/  DCLKCON_DCLK1_DIV_SHIFT ; 
 int NOTIFY_DONE ; 
 unsigned long POST_RATE_CHANGE ; 
 int /*<<< orphan*/  s3c24xx_dclk_update_cmp (struct s3c24xx_dclk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s3c24xx_dclk* to_s3c24xx_dclk1 (struct notifier_block*) ; 

__attribute__((used)) static int s3c24xx_dclk1_div_notify(struct notifier_block *nb,
			       unsigned long event, void *data)
{
	struct s3c24xx_dclk *s3c24xx_dclk = to_s3c24xx_dclk1(nb);

	if (event == POST_RATE_CHANGE) {
		s3c24xx_dclk_update_cmp(s3c24xx_dclk,
			DCLKCON_DCLK1_DIV_SHIFT, DCLKCON_DCLK1_CMP_SHIFT);
	}

	return NOTIFY_DONE;
}