#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum spi_signal_type { ____Placeholder_spi_signal_type } spi_signal_type ;
struct TYPE_3__ {int value; char const* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* signal_types ; 

__attribute__((used)) static inline const char *spi_signal_to_string(enum spi_signal_type type)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(signal_types); i++) {
		if (type == signal_types[i].value)
			return signal_types[i].name;
	}
	return NULL;
}