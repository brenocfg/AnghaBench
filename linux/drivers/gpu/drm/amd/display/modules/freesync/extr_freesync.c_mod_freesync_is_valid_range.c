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
typedef  int uint32_t ;
struct mod_freesync {int dummy; } ;
struct dc_stream_state {int dummy; } ;

/* Variables and functions */
 unsigned long long div_u64 (unsigned long long,int) ; 
 unsigned long long mod_freesync_calc_nominal_field_rate (struct dc_stream_state const*) ; 

bool mod_freesync_is_valid_range(struct mod_freesync *mod_freesync,
		const struct dc_stream_state *stream,
		uint32_t min_refresh_cap_in_uhz,
		uint32_t max_refresh_cap_in_uhz,
		uint32_t min_refresh_request_in_uhz,
		uint32_t max_refresh_request_in_uhz)
{
	/* Calculate nominal field rate for stream */
	unsigned long long nominal_field_rate_in_uhz =
			mod_freesync_calc_nominal_field_rate(stream);

	/* Typically nominal refresh calculated can have some fractional part.
	 * Allow for some rounding error of actual video timing by taking floor
	 * of caps and request. Round the nominal refresh rate.
	 *
	 * Dividing will convert everything to units in Hz although input
	 * variable name is in uHz!
	 *
	 * Also note, this takes care of rounding error on the nominal refresh
	 * so by rounding error we only expect it to be off by a small amount,
	 * such as < 0.1 Hz. i.e. 143.9xxx or 144.1xxx.
	 *
	 * Example 1. Caps    Min = 40 Hz, Max = 144 Hz
	 *            Request Min = 40 Hz, Max = 144 Hz
	 *                    Nominal = 143.5x Hz rounded to 144 Hz
	 *            This function should allow this as valid request
	 *
	 * Example 2. Caps    Min = 40 Hz, Max = 144 Hz
	 *            Request Min = 40 Hz, Max = 144 Hz
	 *                    Nominal = 144.4x Hz rounded to 144 Hz
	 *            This function should allow this as valid request
	 *
	 * Example 3. Caps    Min = 40 Hz, Max = 144 Hz
	 *            Request Min = 40 Hz, Max = 144 Hz
	 *                    Nominal = 120.xx Hz rounded to 120 Hz
	 *            This function should return NOT valid since the requested
	 *            max is greater than current timing's nominal
	 *
	 * Example 4. Caps    Min = 40 Hz, Max = 120 Hz
	 *            Request Min = 40 Hz, Max = 120 Hz
	 *                    Nominal = 144.xx Hz rounded to 144 Hz
	 *            This function should return NOT valid since the nominal
	 *            is greater than the capability's max refresh
	 */
	nominal_field_rate_in_uhz =
			div_u64(nominal_field_rate_in_uhz + 500000, 1000000);
	min_refresh_cap_in_uhz /= 1000000;
	max_refresh_cap_in_uhz /= 1000000;
	min_refresh_request_in_uhz /= 1000000;
	max_refresh_request_in_uhz /= 1000000;

	// Check nominal is within range
	if (nominal_field_rate_in_uhz > max_refresh_cap_in_uhz ||
		nominal_field_rate_in_uhz < min_refresh_cap_in_uhz)
		return false;

	// If nominal is less than max, limit the max allowed refresh rate
	if (nominal_field_rate_in_uhz < max_refresh_cap_in_uhz)
		max_refresh_cap_in_uhz = nominal_field_rate_in_uhz;

	// Don't allow min > max
	if (min_refresh_request_in_uhz > max_refresh_request_in_uhz)
		return false;

	// Check min is within range
	if (min_refresh_request_in_uhz > max_refresh_cap_in_uhz ||
		min_refresh_request_in_uhz < min_refresh_cap_in_uhz)
		return false;

	// Check max is within range
	if (max_refresh_request_in_uhz > max_refresh_cap_in_uhz ||
		max_refresh_request_in_uhz < min_refresh_cap_in_uhz)
		return false;

	// For variable range, check for at least 10 Hz range
	if ((max_refresh_request_in_uhz != min_refresh_request_in_uhz) &&
		(max_refresh_request_in_uhz - min_refresh_request_in_uhz < 10))
		return false;

	return true;
}