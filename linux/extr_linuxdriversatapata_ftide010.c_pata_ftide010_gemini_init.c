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
struct ftide010 {int dummy; } ;
struct ata_port_info {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 

__attribute__((used)) static int pata_ftide010_gemini_init(struct ftide010 *ftide,
				     struct ata_port_info *pi,
				     bool is_ata1)
{
	return -ENOTSUPP;
}