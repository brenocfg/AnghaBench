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
struct i2400m_fw {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2400m_fw_destroy ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void i2400m_fw_put(struct i2400m_fw *i2400m_fw)
{
	kref_put(&i2400m_fw->kref, i2400m_fw_destroy);
}