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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct device* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device *cros_ec_cec_find_hdmi_dev(struct device *dev,
						const char **conn)
{
	return ERR_PTR(-ENODEV);
}