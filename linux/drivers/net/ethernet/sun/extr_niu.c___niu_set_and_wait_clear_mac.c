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
typedef  scalar_t__ u64 ;
struct niu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int __niu_wait_bits_clear_mac (struct niu*,unsigned long,scalar_t__,int,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,unsigned long long,char const*,unsigned long long) ; 
 scalar_t__ nr64_mac (unsigned long) ; 
 int /*<<< orphan*/  nw64_mac (unsigned long,scalar_t__) ; 

__attribute__((used)) static int __niu_set_and_wait_clear_mac(struct niu *np, unsigned long reg,
					u64 bits, int limit, int delay,
					const char *reg_name)
{
	int err;

	nw64_mac(reg, bits);
	err = __niu_wait_bits_clear_mac(np, reg, bits, limit, delay);
	if (err)
		netdev_err(np->dev, "bits (%llx) of register %s would not clear, val[%llx]\n",
			   (unsigned long long)bits, reg_name,
			   (unsigned long long)nr64_mac(reg));
	return err;
}