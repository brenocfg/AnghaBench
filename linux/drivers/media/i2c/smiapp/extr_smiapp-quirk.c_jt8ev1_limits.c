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
struct smiapp_sensor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMIAPP_LIMIT_MIN_LINE_BLANKING_PCK_BIN ; 
 int /*<<< orphan*/  SMIAPP_LIMIT_X_ADDR_MAX ; 
 int /*<<< orphan*/  smiapp_replace_limit (struct smiapp_sensor*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int jt8ev1_limits(struct smiapp_sensor *sensor)
{
	smiapp_replace_limit(sensor, SMIAPP_LIMIT_X_ADDR_MAX, 4271);
	smiapp_replace_limit(sensor,
			     SMIAPP_LIMIT_MIN_LINE_BLANKING_PCK_BIN, 184);

	return 0;
}