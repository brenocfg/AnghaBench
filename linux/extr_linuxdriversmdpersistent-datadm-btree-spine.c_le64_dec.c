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
typedef  int /*<<< orphan*/  v_le ;
struct dm_transaction_manager {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  dm_tm_dec (struct dm_transaction_manager*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static void le64_dec(void *context, const void *value_le)
{
	struct dm_transaction_manager *tm = context;
	__le64 v_le;

	memcpy(&v_le, value_le, sizeof(v_le));
	dm_tm_dec(tm, le64_to_cpu(v_le));
}