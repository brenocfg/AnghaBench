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
struct saa7164_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa7164_encoder_configure (struct saa7164_port*) ; 

__attribute__((used)) static int saa7164_encoder_initialize(struct saa7164_port *port)
{
	saa7164_encoder_configure(port);
	return 0;
}