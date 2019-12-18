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
struct wacom {scalar_t__ idx; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_clear_data_buf(struct wacom *wacom)
{
	memset(wacom->data, 0, DATA_SIZE);
	wacom->idx = 0;
}