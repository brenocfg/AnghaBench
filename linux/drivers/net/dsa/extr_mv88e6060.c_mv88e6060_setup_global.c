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
struct mv88e6060_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_ATU_CONTROL ; 
 int /*<<< orphan*/  GLOBAL_ATU_CONTROL_LEARNDIS ; 
 int /*<<< orphan*/  GLOBAL_CONTROL ; 
 int /*<<< orphan*/  GLOBAL_CONTROL_MAX_FRAME_1536 ; 
 int /*<<< orphan*/  REG_GLOBAL ; 
 int reg_write (struct mv88e6060_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6060_setup_global(struct mv88e6060_priv *priv)
{
	int ret;

	/* Disable discarding of frames with excessive collisions,
	 * set the maximum frame size to 1536 bytes, and mask all
	 * interrupt sources.
	 */
	ret = reg_write(priv, REG_GLOBAL, GLOBAL_CONTROL,
			GLOBAL_CONTROL_MAX_FRAME_1536);
	if (ret)
		return ret;

	/* Disable automatic address learning.
	 */
	return reg_write(priv, REG_GLOBAL, GLOBAL_ATU_CONTROL,
			 GLOBAL_ATU_CONTROL_LEARNDIS);
}