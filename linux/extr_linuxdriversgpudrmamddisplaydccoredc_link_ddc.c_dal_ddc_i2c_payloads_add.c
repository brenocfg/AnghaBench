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
typedef  scalar_t__ uint32_t ;
struct i2c_payloads {int /*<<< orphan*/  payloads; } ;
struct i2c_payload {int write; scalar_t__ address; int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDC_MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ EDID_SEGMENT_SIZE ; 
 int /*<<< orphan*/  dal_vector_append (int /*<<< orphan*/ *,struct i2c_payload*) ; 

void dal_ddc_i2c_payloads_add(
	struct i2c_payloads *payloads,
	uint32_t address,
	uint32_t len,
	uint8_t *data,
	bool write)
{
	uint32_t payload_size = EDID_SEGMENT_SIZE;
	uint32_t pos;

	for (pos = 0; pos < len; pos += payload_size) {
		struct i2c_payload payload = {
			.write = write,
			.address = address,
			.length = DDC_MIN(payload_size, len - pos),
			.data = data + pos };
		dal_vector_append(&payloads->payloads, &payload);
	}

}