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
struct i2400m_pld {int /*<<< orphan*/  val; } ;
typedef  enum i2400m_pt { ____Placeholder_i2400m_pt } i2400m_pt ;

/* Variables and functions */
 int I2400M_PLD_TYPE_MASK ; 
 int I2400M_PLD_TYPE_SHIFT ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
enum i2400m_pt i2400m_pld_type(const struct i2400m_pld *pld)
{
	return (I2400M_PLD_TYPE_MASK & le32_to_cpu(pld->val))
		>> I2400M_PLD_TYPE_SHIFT;
}