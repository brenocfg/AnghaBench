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
struct aux_payloads {int /*<<< orphan*/  payloads; } ;
struct aux_payload {int i2c_over_aux; int write; scalar_t__ address; int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDC_MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ DEFAULT_AUX_MAX_DATA_SIZE ; 
 int /*<<< orphan*/  dal_vector_append (int /*<<< orphan*/ *,struct aux_payload*) ; 

void dal_ddc_aux_payloads_add(
	struct aux_payloads *payloads,
	uint32_t address,
	uint32_t len,
	uint8_t *data,
	bool write)
{
	uint32_t payload_size = DEFAULT_AUX_MAX_DATA_SIZE;
	uint32_t pos;

	for (pos = 0; pos < len; pos += payload_size) {
		struct aux_payload payload = {
			.i2c_over_aux = true,
			.write = write,
			.address = address,
			.length = DDC_MIN(payload_size, len - pos),
			.data = data + pos };
		dal_vector_append(&payloads->payloads, &payload);
	}
}