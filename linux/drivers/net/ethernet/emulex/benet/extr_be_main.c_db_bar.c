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
struct be_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ be_virtfn (struct be_adapter*) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 

__attribute__((used)) static int db_bar(struct be_adapter *adapter)
{
	if (lancer_chip(adapter) || be_virtfn(adapter))
		return 0;
	else
		return 4;
}