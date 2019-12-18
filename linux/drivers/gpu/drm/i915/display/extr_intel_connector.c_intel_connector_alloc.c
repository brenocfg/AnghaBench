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
struct intel_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ intel_connector_init (struct intel_connector*) ; 
 int /*<<< orphan*/  kfree (struct intel_connector*) ; 
 struct intel_connector* kzalloc (int,int /*<<< orphan*/ ) ; 

struct intel_connector *intel_connector_alloc(void)
{
	struct intel_connector *connector;

	connector = kzalloc(sizeof(*connector), GFP_KERNEL);
	if (!connector)
		return NULL;

	if (intel_connector_init(connector) < 0) {
		kfree(connector);
		return NULL;
	}

	return connector;
}