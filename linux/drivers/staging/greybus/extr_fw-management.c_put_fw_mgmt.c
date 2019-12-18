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
struct fw_mgmt {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_mgmt_kref_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_fw_mgmt(struct fw_mgmt *fw_mgmt)
{
	kref_put(&fw_mgmt->kref, fw_mgmt_kref_release);
}