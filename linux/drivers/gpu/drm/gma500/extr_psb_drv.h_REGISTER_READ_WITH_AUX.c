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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_READ_AUX (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t REGISTER_READ_WITH_AUX(struct drm_device *dev,
					      uint32_t reg, int aux)
{
	uint32_t val;

	if (aux)
		val = REG_READ_AUX(reg);
	else
		val = REG_READ(reg);

	return val;
}