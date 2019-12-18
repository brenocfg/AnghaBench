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
 int /*<<< orphan*/  dev_warn (struct device*,char*,char const* const,int) ; 
 int request_module (char const* const) ; 

__attribute__((used)) static int netup_unidvb_request_modules(struct device *dev)
{
	static const char * const modules[] = {
		"lnbh25", "ascot2e", "horus3a", "cxd2841er", "helene", NULL
	};
	const char * const *curr_mod = modules;
	int err;

	while (*curr_mod != NULL) {
		err = request_module(*curr_mod);
		if (err) {
			dev_warn(dev, "request_module(%s) failed: %d\n",
				*curr_mod, err);
		}
		++curr_mod;
	}
	return 0;
}