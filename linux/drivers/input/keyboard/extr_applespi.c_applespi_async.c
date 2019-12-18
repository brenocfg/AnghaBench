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
struct spi_message {void (* complete ) (void*) ;struct applespi_data* context; } ;
struct applespi_data {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int spi_async (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int applespi_async(struct applespi_data *applespi,
			  struct spi_message *message, void (*complete)(void *))
{
	message->complete = complete;
	message->context = applespi;

	return spi_async(applespi->spi, message);
}