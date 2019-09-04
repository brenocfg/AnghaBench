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
typedef  int /*<<< orphan*/  u32 ;
struct ql3_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_LINK_OPTICAL ; 
 int /*<<< orphan*/  SUPPORTED_OPTICAL_MODES ; 
 int /*<<< orphan*/  SUPPORTED_TP_MODES ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 ql_supported_modes(struct ql3_adapter *qdev)
{
	if (test_bit(QL_LINK_OPTICAL, &qdev->flags))
		return SUPPORTED_OPTICAL_MODES;

	return SUPPORTED_TP_MODES;
}