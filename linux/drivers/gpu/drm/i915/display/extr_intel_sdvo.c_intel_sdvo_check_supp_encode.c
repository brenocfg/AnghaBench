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
struct intel_sdvo_encode {int dummy; } ;
struct intel_sdvo {int dummy; } ;
typedef  int /*<<< orphan*/  encode ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  SDVO_CMD_GET_SUPP_ENCODE ; 
 int intel_sdvo_get_value (struct intel_sdvo*,int /*<<< orphan*/ ,struct intel_sdvo_encode*,int) ; 

__attribute__((used)) static bool intel_sdvo_check_supp_encode(struct intel_sdvo *intel_sdvo)
{
	struct intel_sdvo_encode encode;

	BUILD_BUG_ON(sizeof(encode) != 2);
	return intel_sdvo_get_value(intel_sdvo,
				  SDVO_CMD_GET_SUPP_ENCODE,
				  &encode, sizeof(encode));
}