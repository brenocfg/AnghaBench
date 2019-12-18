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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct dc_link {int /*<<< orphan*/  ctx; int /*<<< orphan*/  aux_access_disabled; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;

/* Variables and functions */
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
 int /*<<< orphan*/  dm_helpers_dp_write_dpcd (int /*<<< orphan*/ ,struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

enum dc_status core_link_write_dpcd(
	struct dc_link *link,
	uint32_t address,
	const uint8_t *data,
	uint32_t size)
{
	if (!link->aux_access_disabled &&
			!dm_helpers_dp_write_dpcd(link->ctx,
			link, address, data, size)) {
		return DC_ERROR_UNEXPECTED;
	}

	return DC_OK;
}