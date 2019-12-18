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
struct uwire_state {int dummy; } ;
struct spi_device {struct uwire_state* controller_state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct uwire_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int uwire_setup_transfer (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uwire_setup(struct spi_device *spi)
{
	struct uwire_state *ust = spi->controller_state;

	if (ust == NULL) {
		ust = kzalloc(sizeof(*ust), GFP_KERNEL);
		if (ust == NULL)
			return -ENOMEM;
		spi->controller_state = ust;
	}

	return uwire_setup_transfer(spi, NULL);
}