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
struct tmp102 {int /*<<< orphan*/  config_orig; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMP102_CONF_REG ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tmp102_restore_config(void *data)
{
	struct tmp102 *tmp102 = data;

	regmap_write(tmp102->regmap, TMP102_CONF_REG, tmp102->config_orig);
}