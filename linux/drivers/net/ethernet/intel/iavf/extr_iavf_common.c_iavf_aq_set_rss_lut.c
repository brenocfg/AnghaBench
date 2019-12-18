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
typedef  int /*<<< orphan*/  u16 ;
struct iavf_hw {int dummy; } ;
typedef  enum iavf_status { ____Placeholder_iavf_status } iavf_status ;

/* Variables and functions */
 int iavf_aq_get_set_rss_lut (struct iavf_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

enum iavf_status iavf_aq_set_rss_lut(struct iavf_hw *hw, u16 vsi_id,
				     bool pf_lut, u8 *lut, u16 lut_size)
{
	return iavf_aq_get_set_rss_lut(hw, vsi_id, pf_lut, lut, lut_size, true);
}