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
struct ishtp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_BUILD_HEADER (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IPC_PROTOCOL_ISHTP ; 

__attribute__((used)) static uint32_t ish_ipc_get_header(struct ishtp_device *dev, int length,
				   int busy)
{
	uint32_t drbl_val;

	drbl_val = IPC_BUILD_HEADER(length, IPC_PROTOCOL_ISHTP, busy);

	return drbl_val;
}