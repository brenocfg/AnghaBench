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
typedef  int /*<<< orphan*/  u8 ;
struct av7110 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AudioDAC ; 
 int /*<<< orphan*/  COMTYPE_AUDIODAC ; 
 int av7110_fw_cmd (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int SendDAC(struct av7110 *av7110, u8 addr, u8 data)
{
	return av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, AudioDAC, 2, addr, data);
}