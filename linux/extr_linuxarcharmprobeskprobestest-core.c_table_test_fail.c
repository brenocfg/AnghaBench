#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bits; } ;
struct TYPE_3__ {int /*<<< orphan*/  bits; } ;
struct decode_header {TYPE_2__ value; TYPE_1__ mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int table_test_fail(const struct decode_header *h, const char* message)
{

	pr_err("FAIL: kprobes test failure \"%s\" (mask %08x, value %08x)\n",
					message, h->mask.bits, h->value.bits);
	return -EINVAL;
}