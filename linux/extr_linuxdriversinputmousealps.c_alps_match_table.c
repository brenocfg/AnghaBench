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
struct alps_protocol_info {int dummy; } ;
struct alps_model_info {struct alps_protocol_info const protocol_info; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct alps_model_info*) ; 
 struct alps_model_info* alps_model_data ; 
 int /*<<< orphan*/  memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const struct alps_protocol_info *alps_match_table(unsigned char *e7,
							 unsigned char *ec)
{
	const struct alps_model_info *model;
	int i;

	for (i = 0; i < ARRAY_SIZE(alps_model_data); i++) {
		model = &alps_model_data[i];

		if (!memcmp(e7, model->signature, sizeof(model->signature)))
			return &model->protocol_info;
	}

	return NULL;
}