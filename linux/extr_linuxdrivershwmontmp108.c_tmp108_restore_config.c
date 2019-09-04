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
struct tmp108 {int /*<<< orphan*/  orig_config; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMP108_REG_CONF ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tmp108_restore_config(void *data)
{
	struct tmp108 *tmp108 = data;

	regmap_write(tmp108->regmap, TMP108_REG_CONF, tmp108->orig_config);
}