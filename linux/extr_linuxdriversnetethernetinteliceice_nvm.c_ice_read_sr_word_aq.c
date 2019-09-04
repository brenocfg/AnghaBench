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
typedef  int /*<<< orphan*/  u16 ;
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ice_read_sr_aq (struct ice_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_read_sr_word_aq(struct ice_hw *hw, u16 offset, u16 *data)
{
	enum ice_status status;

	status = ice_read_sr_aq(hw, offset, 1, data, true);
	if (!status)
		*data = le16_to_cpu(*(__le16 *)data);

	return status;
}