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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  H2C_PKT_CATEGORY ; 
 int /*<<< orphan*/  H2C_PKT_CMD_ID ; 
 int /*<<< orphan*/  SET_PKT_H2C_CATEGORY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PKT_H2C_CMD_ID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PKT_H2C_SUB_CMD_ID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rtw_h2c_pkt_set_header(u8 *h2c_pkt, u8 sub_id)
{
	SET_PKT_H2C_CATEGORY(h2c_pkt, H2C_PKT_CATEGORY);
	SET_PKT_H2C_CMD_ID(h2c_pkt, H2C_PKT_CMD_ID);
	SET_PKT_H2C_SUB_CMD_ID(h2c_pkt, sub_id);
}