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
struct regmap {int dummy; } ;
struct mn88443x_priv {struct regmap* regmap_t; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWDSET ; 
 int /*<<< orphan*/  PWDSET_OFDMPD_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mn88443x_t_wake(struct mn88443x_priv *chip)
{
	struct regmap *r_t = chip->regmap_t;

	regmap_update_bits(r_t, PWDSET, PWDSET_OFDMPD_MASK, 0);
}