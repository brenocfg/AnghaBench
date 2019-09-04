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
struct dc_context {int dummy; } ;
struct aux_payloads {int /*<<< orphan*/  payloads; } ;
struct aux_payload {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ dal_vector_construct (int /*<<< orphan*/ *,struct dc_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct aux_payloads*) ; 
 struct aux_payloads* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct aux_payloads *dal_ddc_aux_payloads_create(struct dc_context *ctx, uint32_t count)
{
	struct aux_payloads *payloads;

	payloads = kzalloc(sizeof(struct aux_payloads), GFP_KERNEL);

	if (!payloads)
		return NULL;

	if (dal_vector_construct(
		&payloads->payloads, ctx, count, sizeof(struct aux_payload)))
		return payloads;

	kfree(payloads);
	return NULL;
}