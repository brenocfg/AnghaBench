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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct ixgbevf_reg_test {scalar_t__ reg; scalar_t__ array_len; int test_type; int /*<<< orphan*/  write; int /*<<< orphan*/  mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_addr; } ;
struct ixgbevf_adapter {TYPE_2__ hw; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IXGBE_REMOVED (int /*<<< orphan*/ ) ; 
#define  PATTERN_TEST 133 
#define  SET_READ_TEST 132 
#define  TABLE32_TEST 131 
#define  TABLE64_TEST_HI 130 
#define  TABLE64_TEST_LO 129 
#define  WRITE_NO_TEST 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ixgbe_write_reg (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int reg_pattern_test (struct ixgbevf_adapter*,int*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reg_set_and_check (struct ixgbevf_adapter*,int*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ixgbevf_reg_test* reg_test_vf ; 

__attribute__((used)) static int ixgbevf_reg_test(struct ixgbevf_adapter *adapter, u64 *data)
{
	const struct ixgbevf_reg_test *test;
	u32 i;

	if (IXGBE_REMOVED(adapter->hw.hw_addr)) {
		dev_err(&adapter->pdev->dev,
			"Adapter removed - register test blocked\n");
		*data = 1;
		return 1;
	}
	test = reg_test_vf;

	/* Perform the register test, looping through the test table
	 * until we either fail or reach the null entry.
	 */
	while (test->reg) {
		for (i = 0; i < test->array_len; i++) {
			bool b = false;

			switch (test->test_type) {
			case PATTERN_TEST:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 0x40),
						     test->mask,
						     test->write);
				break;
			case SET_READ_TEST:
				b = reg_set_and_check(adapter, data,
						      test->reg + (i * 0x40),
						      test->mask,
						      test->write);
				break;
			case WRITE_NO_TEST:
				ixgbe_write_reg(&adapter->hw,
						test->reg + (i * 0x40),
						test->write);
				break;
			case TABLE32_TEST:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 4),
						     test->mask,
						     test->write);
				break;
			case TABLE64_TEST_LO:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 8),
						     test->mask,
						     test->write);
				break;
			case TABLE64_TEST_HI:
				b = reg_pattern_test(adapter, data,
						     test->reg + 4 + (i * 8),
						     test->mask,
						     test->write);
				break;
			}
			if (b)
				return 1;
		}
		test++;
	}

	*data = 0;
	return *data;
}