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
struct octeon_device {int dummy; } ;
struct octeon_config {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_CONF (struct octeon_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN6XXX (struct octeon_device*) ; 
 int /*<<< orphan*/  cn23xx_pf ; 
 int /*<<< orphan*/  cn23xx_vf ; 
 int /*<<< orphan*/  cn6xxx ; 

struct octeon_config *octeon_get_conf(struct octeon_device *oct)
{
	struct octeon_config *default_oct_conf = NULL;

	/* check the OCTEON Device model & return the corresponding octeon
	 * configuration
	 */

	if (OCTEON_CN6XXX(oct)) {
		default_oct_conf =
			(struct octeon_config *)(CHIP_CONF(oct, cn6xxx));
	} else if (OCTEON_CN23XX_PF(oct)) {
		default_oct_conf = (struct octeon_config *)
			(CHIP_CONF(oct, cn23xx_pf));
	} else if (OCTEON_CN23XX_VF(oct)) {
		default_oct_conf = (struct octeon_config *)
			(CHIP_CONF(oct, cn23xx_vf));
	}
	return default_oct_conf;
}