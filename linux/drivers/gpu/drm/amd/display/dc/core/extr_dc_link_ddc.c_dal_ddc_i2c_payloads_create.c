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
typedef  int /*<<< orphan*/  uint32_t ;
struct i2c_payloads {int /*<<< orphan*/  payloads; } ;
struct i2c_payload {int dummy; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ dal_vector_construct (int /*<<< orphan*/ *,struct dc_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct i2c_payloads*) ; 
 struct i2c_payloads* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i2c_payloads *dal_ddc_i2c_payloads_create(struct dc_context *ctx, uint32_t count)
{
	struct i2c_payloads *payloads;

	payloads = kzalloc(sizeof(struct i2c_payloads), GFP_KERNEL);

	if (!payloads)
		return NULL;

	if (dal_vector_construct(
		&payloads->payloads, ctx, count, sizeof(struct i2c_payload)))
		return payloads;

	kfree(payloads);
	return NULL;

}