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
 int /*<<< orphan*/  SCALER_DST_CFG ; 
 int /*<<< orphan*/  SCALER_DST_CFG_SET_COLOR_FORMAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scaler_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void scaler_set_dst_fmt(struct scaler_context *scaler,
	u32 dst_fmt)
{
	u32 val;

	val = SCALER_DST_CFG_SET_COLOR_FORMAT(dst_fmt);
	scaler_write(val, SCALER_DST_CFG);
}