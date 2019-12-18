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
struct anybuss_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void *
anybuss_get_drvdata(const struct anybuss_client *client)
{
	return dev_get_drvdata(&client->dev);
}