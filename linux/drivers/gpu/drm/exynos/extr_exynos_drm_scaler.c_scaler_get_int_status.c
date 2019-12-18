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
struct scaler_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALER_INT_STATUS ; 
 int /*<<< orphan*/  scaler_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scaler_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 scaler_get_int_status(struct scaler_context *scaler)
{
	u32 val = scaler_read(SCALER_INT_STATUS);

	scaler_write(val, SCALER_INT_STATUS);

	return val;
}